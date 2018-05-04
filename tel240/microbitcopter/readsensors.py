import microbit as m

def check_button():
    if m.button_b.is_pressed():
        m.display.show(m.Image.HAPPY)
    else:
        m.display.show(m.Image.SAD)

def print_csv(values):
    last = len(values)-1
    for i, v in enumerate(values):
        m.uart.write(str(v))
        if i != last:
            m.uart.write(',')
    m.uart.write('\r\n')

m.uart.init(115200)
i = 0
while True:
    x,y,z = m.accelerometer.get_values()
    t = m.running_time()
    i += 1
    print_csv((i, t, x, y, z))
    
    check_button()
    m.sleep(100)

