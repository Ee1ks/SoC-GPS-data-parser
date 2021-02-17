import serial
import socket

HOST = '0.0.0.0'  # Standard loopback interface address (localhost)
PORT =  8082        # Port to listen on (non-privileged ports are > 1023)


def send_data(data, s):
    print(data)
    s.sendall(data)
    return


def parse_data(data, s):
    split_data = data.split(',')
    if split_data[0] == "$GNGGA":
        send_data(str.encode("0,"+data[1:]),s)
        send_data(str.encode("606,"+split_data[1][:2]+":"+split_data[1][2:4]+":"+split_data[1][4:6]),s)
    elif split_data[0] == "$GNRMC":
        send_data(str.encode("80,"+data[1:]),s)
    #     print("RMC time: {}".format(split_data[1]))
    elif split_data[0] == "$GNVTG":
        send_data(str.encode("160,"+data[1:]),s)
    #     print("VTG SPEED: {}".format(split_data[5]))
    elif split_data[0] == "$GNGLL":
        send_data(str.encode("240,"+data[1:]),s)
    #     print("GLL STUFF: {}".format(split_data[1]))
    else:
        return


# Open serial port
ser = serial.Serial(
    port="COM7", baudrate=9600, bytesize=8,
    timeout=2, stopbits=serial.STOPBITS_ONE
)

# open client
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((HOST, PORT))

while(1):

    # Wait until there is data waiting in the serial buffer
    if(ser.in_waiting > 0):
        # Read data from buffer
        serialString = ser.readline()
        # Decode to ASCII
        data = serialString.decode('Ascii')
        # Parse data
        parse_data(data, s)
