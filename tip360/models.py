
## Return bitrates (bits/second) for different data/feature representations
def audio_size(samplerate, bits=4):
    return samplerate * bits

def melspec_size(frame_shift, n_mels, bits=4):
    n_frames = 1.0/frame_shift
    return n_frames * n_mels * bits

def mfcc_size(frame_shift, n_mfcc, bits=4):
    n_frames = 1.0/frame_shift
    return n_frames * n_mfcc * bits

def summaries_size(window_length, n_features, bits=4):
    n_summaries = 1.0/window_length
    return n_summaries * n_features * bits

# energy
# TODO: battery size constraints
# 
def battery_life_days(capacity, drain):
    hours = capacity / drain
    return hours/24


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


def octave_bands_ram(window, samples_second=8, n_bands=31, precision=2):
    samples = window * samples_second
    bytes = samples * n_bands * precision 
    return bytes

def radio_time(bytes, rate=50000, setup_time=10):
    transmit_time = bytes / rate
    return setup_time + transmit_time

# Activites
#  mic-read
#  noise-calculate
#  noiseid-calculate
#  transmit
#
# Aspects
#  RAM use
#  energy use (cpu usage, data produced)

# TODO: model RAM needed
# TODO: model temp storage needed between transmission intervals
# TODO: model data needs for noise measurement
# TODO: model CPU capacity
def noise_sensor(ram_kb=40,
        transmit_period_hours = 24,
        noiseid_window=60,
        battery_selfdischarge=0.05,
        battery_days=365,
        battery_mah=3000):

    import z3

    cpu_ram = z3.Int('cpu_ram')
    energy_budget = z3.Int('energy_budget') # microamps/day

    # take into account self-discharge
    battery_mah = battery_mah * (1.0-battery_selfdischarge)

    battery_uas = battery_mah * 1000 * 3600
    energy_day = battery_uas / battery_days

    # FIXME: calculate from activities
    transmit_size = 2048 + 30000
    transmit_time = radio_time(transmit_size)
    
    transmit_period = transmit_period_hours / 24*60*60

    ram_use = [
        z3.IntVal(256*8), # audio buffers
        z3.IntVal(2048), # transmit payload. TODO: function of transmit_interval
        z3.IntVal(octave_bands_ram(noiseid_window)),
    ]
    
    cpu_sleep_a = 10e-6
    cpu_run_a = 1e-3
    modem_a = 50e-3

    def energy(amp, seconds=1.0, period=1.0):
        ua = cpu_run_a*1e6
        dutycycle = seconds / period
        return ua * dutycycle

    energy_use = [
        z3.RealVal(energy(cpu_sleep_a)),
        z3.RealVal(energy(cpu_run_a, 10e-6, 1/1000)), # audio read
        z3.RealVal(energy(cpu_run_a, 100e-6, 1/1000)), # noise calc
        z3.RealVal(energy(modem_a, transmit_time, transmit_period)), # transmit
    ]

    constraints = [
        cpu_ram == ram_kb*1000,
        z3.Sum(ram_use) < cpu_ram,
        energy_budget == energy_day,
        z3.Sum(energy_use) < energy_budget,
    ] 

    s = z3.Solver()
    for c in constraints:
        s.add(c)
    return s

def test_pass():
    m = noise_sensor()
    s = m.check()
    assert str(s) == 'sat', m

def test_fails():
    m = noise_sensor(ram_kb=1)
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
    noise_sensor()
 

if __name__ == '__main__':
    main()
