# shushudang_embedded

# arduino_upper  
1. digital read from raspi : 2 Digital Input  
2. send on/off signal via i2c for each arduino.  
pause(0-1)/intensity(0-3)/temp(0-3)  
ex) 223  
3.  
```{.python}
if ((pause==1) or digitalread(raspi)==off):
    switch.off()
else:
    pwm.write(세기,온도)
```
