
import math


def mic_signal(pascal, mic_db, pref=20e-6):
    spl = 20*math.log(pascal/pref, 10)
    gain = 10**(mic_db/20)
    return 1 * pascal * gain 


# Maxprice kr 49,- pr døgn opp til 9,5 GB
# GPRS max should be able to do 7500 MB in 24hours. Making monthly dumps viable (ignoring power concerns...)
# Ved 5 GB/mnd strupes hastigheten til 128 kb/s ut måneden
talkmore = {
    0: 2.0,
    5000: (199/5000),
    10000: (299/10000),
}
mycall = {
    0: 2.49,
    1000: (79/1000),
    3000: (149/3000),
    10000: (299/10000),
}
onecall = {
    0: 1.89,
    1000: (79/1000),
    3000: (130/3000),
    5000: (199/5000),
    10000: (299/10000),
}

def transmit_costs(bytes, pricebreaks):
    pass


def octave_bands_ram(window, samples_second, n_bands=31, precision=2):
    samples = window * samples_second
    bytes = samples * n_bands * precision 
    return bytes

def radio_time(bytes, rate=50000, setup_time=10):
    transmit_time = bytes / rate
    return setup_time + transmit_time


def noise_sensor(ram_kb=32,
        storage_kb=128,
        transmit_period_hours = 12,
        noise_window=60,
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

import pytest

@pytest.mark.parametrize('model', MODEL_UNSAT.keys())
def test_fails(model):
    m = MODEL_UNSAT.get(model)
    s = m.check()
    assert str(s) == 'unsat', m

def temp():
    frame_shift = 512/44100

    audio = audio_size(44100, bits=16)
    mels = melspec_size(frame_shift, 64, bits=8)
    mfccs = mfcc_size(frame_shift, 20, bits=32)

    transmit_rate = 85.6e3 # gprs
    price_per_mb = 2.0 # NOK
    price_per_byte = price_per_mb / 1e6

    recording_length = 10
    time_between_recordings = 60
    ratio_recordings_sent = 0.01
    
    seconds_timeperiod = 30*24*3600
    n_recordings = seconds_timeperiod / time_between_recordings
    recorded_seconds_timeperiod = n_recordings * recording_length

    compression_ratio = 0.1
    bitrate_avg = ratio_recordings_sent*mels*compression_ratio

    print('sent', ratio_recordings_sent*n_recordings)

    bytes_timeperiod = recorded_seconds_timeperiod * (bitrate_avg/8)
    price_timeperiod = bytes_timeperiod * price_per_byte
    print('price', price_timeperiod)

    summ = summaries_size(recording_length, 64*2*2, bits=32)

    drain = 0.2e-3
    battery_ah = 3000e-3
    days = battery_life_days(battery_ah, drain)
    print('days', days)

    print(locals())


def main():

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
