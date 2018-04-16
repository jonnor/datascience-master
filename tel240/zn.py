kpc=3.3
tc=0.8

Kc=0.6*kpc
Ti=0.5*tc
Td=0.125*tc

print('ideal coefficients', Kc,Ti,Td)
Ki=Kc/tc
Kd=Kc*Td
print('parallel gains', Kc, Ki,Kd)
