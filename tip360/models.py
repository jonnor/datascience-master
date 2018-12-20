
import math
import numpy
import pytest 


def mic_signal(pascal, mic_db, pref=20e-6):
    spl = 20*math.log(pascal/pref, 10)
    gain = 10**(mic_db/20)
    return 1 * pascal * gain 


# Maxprice kr 49,- pr døgn opp til 9,5 GB
# GPRS max should be able to do 7500 MB in 24hours. Making monthly dumps viable (ignoring power concerns...)
# Ved 5 GB/mnd strupes hastigheten til 128 kb/s ut måneden
talkmore_monthly = 0
talkmore = {
    0: 2.0,
    5000: (199/5000),
    10000: (299/10000),
}
mycall_monthly = 0
mycall = {
    0: 2.49,
    1000: (79/1000),
    3000: (149/3000),
    10000: (299/10000),
}
onecall_monthly = 0,
onecall = {
    0: 1.89,
    1000: (79/1000),
    3000: (130/3000),
    5000: (199/5000),
    10000: (299/10000),
}

# http://www.com4.no/produkter/
com4_monthly = 12
com4 = {
    0: (3.99),
    10: (25/10),
    50: (39/50),
    100: (59/100),
    1000: (89/1000),
}

# https://www.telenor.no/bedrift/iot/abonnement/#tab2=1
# M2M Total
telenor_m2mtotal_monthly = 20
telenor_m2mtotal = {
    0: (6.0),
    10: (29/10),
    100: (50/100),
}

# https://www.telia.no/bedrift/m2m/


def transmit_costs_monthly(bytes, base=com4_monthly, pricebreaks=com4):
    def plan_price(plan_idx, megabytes):
        plan_mb = plans[plan_idx]
        price_mb = pricebreaks[plan_mb]
        not_included = max(megabytes - plan_mb, 0)
        not_included_price_mb = pricebreaks[0]
        return base + (plan_mb*price_mb) + (not_included * not_included_price_mb)

    plans = numpy.array(list(pricebreaks.keys()))
    prices = [ plan_price(i, bytes/1e6) for i, p in enumerate(plans) ]
    return min(prices)


TRANSMIT=[
    (5e6, 12+(5*3.99)),
    (10e6, 12+(10*2.5)),
    (12e6, 12+(10*2.5)+(2*3.99)),
]

@pytest.mark.parametrize('test', TRANSMIT)
def test_transmit_costs(test):
    data, expected = test
    price = transmit_costs_monthly(data)
    assert price == pytest.approx(expected)


def octave_bands_ram(window, samples_second, n_bands=31, precision=2):
    samples = window * samples_second
    bytes = samples * n_bands * precision 
    return bytes

def radio_time(bytes, rate=2500, setup_time=10):
    transmit_time = bytes / rate
    return setup_time + transmit_time


def noise_sensor(ram_kb=32,
        storage_kb=128,
        transmit_period_hours = 1,
        noise_window=1/8,
        noiseid_window=60,
        noiseid_samplerate = 4,
        noiseid_max_percent = 0.01,
        mic_a = 500e-6,
        sleep_a = 250e-6,
        cpu_run_a = 2e-3,
        modem_a = 50e-3,
        battery_selfdischarge=0.05,
        battery_days=365,
        battery_mah=1400):

    import z3

    # take into account self-discharge
    battery_mah = battery_mah * (1.0-battery_selfdischarge)

    battery_uas = battery_mah * 1000 * 3600
    energy_day = battery_uas / battery_days

    transmit_period = transmit_period_hours / 24*60*60

    assert noiseid_samplerate < 10 # keep unintelligeble
    assert noiseid_samplerate > 1 # keep useful

    noiseid_data = octave_bands_ram(noiseid_window, noiseid_samplerate)
    noiseid_max_samples = noiseid_max_percent*(transmit_period_hours*60*60 / noiseid_window)

    noiseid_storage = noiseid_data * noiseid_max_samples
    noise_storage = transmit_period_hours*60*60 / noise_window

    data_sizes = [
        noise_storage,
        noiseid_storage,
    ]
    storage_needed = sum(data_sizes)
    storage_size = storage_kb*1000

    transmit_time = radio_time(sum(data_sizes))
    # noise sent as one packet, noiseid as N packets
    transmit_ram = max(noise_storage, noiseid_data)

    print('t time', transmit_time)

    ram_use = [
        z3.IntVal(256*8), # audio buffers
        z3.IntVal(noiseid_data),
        z3.IntVal(transmit_ram),
    ]
    cpu_ram = z3.Int('cpu_ram')

    cpu_use = [
        (16e-6, 16e-3), # audio read
        (160e-6, 16e-3), # noise calc
        (transmit_time, transmit_period), # transmit
    ]
    cpu_use_sum = sum(t/p for t,p in cpu_use)

    assert cpu_use_sum < 1.0, cpu_use
    assert cpu_use_sum > 0.0, cpu_use

    def energy(amp, seconds=1.0, period=1.0):
        ua = amp*1e6
        dutycycle = seconds / period
        tot = ua * dutycycle
        print('e', tot, dutycycle)
        return tot

    energy_use = [
        z3.RealVal(energy(mic_a)), # base, microphone
        z3.RealVal(energy(sleep_a)), # base, sleeping
        z3.RealVal(energy(modem_a, transmit_time, transmit_period)), # transmit
    ]
    energy_use += [ z3.RealVal(energy(cpu_run_a, *c)) for c in cpu_use ]
    energy_budget = z3.Int('energy_budget')
    energy_spend = z3.Real('energy_use')

    ram_left = z3.Int('ram_left')
    energy_left = z3.Real('energy_left')
    storage_left = z3.Int('storage_left')

    print('b', (energy_day/(1000*24))*battery_days)
    
    constraints = [
        cpu_ram == ram_kb*1000,
        energy_budget == energy_day,
        ram_left == cpu_ram - z3.Sum(ram_use),
        energy_spend == z3.Sum(energy_use),
        energy_left == energy_budget - energy_spend,
        storage_left == z3.IntVal(storage_size) - z3.IntVal(storage_needed),
        ram_left > 0,
        energy_left > 0,
        storage_left > 0,
    ]

    s = z3.Solver()
    for c in constraints:
        s.add(c)
    return s

MODEL_UNSAT = {
    'not enough ram': noise_sensor(ram_kb=1),
    'not enough storage': noise_sensor(storage_kb=1),
}

def test_pass():
    n = noise_sensor(battery_mah=1400)
    s = n.check()
    assert str(s) == 'sat', n

    m = n.model()    
    for v in m:
        print('v', v, m[v])

    assert False


@pytest.mark.parametrize('model', MODEL_UNSAT.keys())
def test_fails(model):
    m = MODEL_UNSAT.get(model)
    s = m.check()
    assert str(s) == 'unsat', m

def temp():

    drain = 0.8e-3
    battery_ah = 9600e-3
    days = battery_life_days(battery_ah, drain)
    print('days', days)

    print(locals())

def daily_data_short_leq(per_second=8):
    return 1*per_second*3600*24

def daily_data_leq_avg(per_minute=1):
    return 1*per_minute*60*24

def main():

    print('Short Leq', 30*daily_data_short_leq()/1e6)
    print('NOK', transmit_costs_monthly(30*daily_data_short_leq()))
    print('current', 300*radio_time(daily_data_short_leq())/(24*3600))

    print('Average Leq', 30*daily_data_leq_avg()/1e6)
    print('NOK', transmit_costs_monthly(30*daily_data_leq_avg()))
    print('current', 300*radio_time(daily_data_leq_avg())/(24*3600))


    """
    with conservative numbers, does not work out for Short Leq.
    Miight be OK if GPRS speed is faster than assumed, and power consumption lower.
    >>> 100 * (300/(3600*24))
    0.3472222222222222
    """

    low = 2e-3 # 40db SPL
    high = 634e-3 # 90 db SPL
    max = 20 # 120 db SPL
    mic_sensitivity = -42

    l = mic_signal(low, mic_sensitivity)
    h = mic_signal(high, mic_sensitivity)
    m = mic_signal(max, mic_sensitivity)
    print('mic signal (mV): {:.2f} - {:.2f}'.format(l*1000, h*1000, m*1000))

    noise_sensor()
 

if __name__ == '__main__':
    main()
