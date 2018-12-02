
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


# TODO: model RAM needed
# TODO: model temp storage needed between transmission intervals
# TODO: model data needs for noise measurement
# TODO: allow hybrid mixture of raw,features,classification-summary

def main():
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

if __name__ == '__main__':
    main()
