
import simpleaudio
import numpy
import pandas
import sys

def main():
    out, files = sys.argv[1], sys.argv[2:]

    filenames = []
    has_birds = []

    print(len(files))
    assert len(files) > 0

    try:
        for i, path in enumerate(files):

            print('{} playing: {}', i, path)
            wav = simpleaudio.WaveObject.from_wave_file(path)
            play = wav.play()
            play.wait_done()

            print("Did file contain bird? y/n")
            inp = input()
            has_bird = None
            if inp not in ('y', 'n'):
                print("ERROR: got", inp)
            else:
                has_bird = inp == 'y'

            print('GT: {},{}', path, has_bird)

            filenames.append(path)
            has_birds.append(has_bird)

    except KeyboardInterrupt:
        df = pandas.DataFrame({
            'file': filenames, 
            'dataset': ['chern'] * len(filenames),
            'hasbird': has_birds,
        })
        df.to_csv(out)

if __name__ == '__main__':
    main()
