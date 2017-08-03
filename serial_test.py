import serial

running = True
ser = serial.Serial('/dev/ttyACM0', 115200)

while running:
  res = input(">> ")
  if res == 'exit':
    running = False
  b = res.encode('utf-8')
  print(res)
  ser.write(b)
  print("SENT!")

print("Exiting...") 
