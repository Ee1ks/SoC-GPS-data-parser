import serial
import socket

HOST = '78.84.96.96'  # Standard loopback interface address (localhost)
PORT =  8086        # Port to listen on (non-privileged ports are > 1023)


def send_data(data, s):
    print(data)
    s.sendall(data)
    return


def parse_data(data, s):
    split_data = data.split(',')
    if split_data[0][1:] == "GNGSV":
        # Any combo satelites in view
        data_string = "1429,"+split_data[3]+"\n"
        extra = 0
        if len(data_string) < 80:
            extra = 80-len(data_string)
        send_data(str.encode(data_string+extra*"-"), s)
    elif split_data[0][1:] == "GLGSV":
        # GLONASS in view
        data_string = "1369,"+split_data[3]+"\n"
        extra = 0
        if len(data_string) < 80:
            extra = 80-len(data_string)
        send_data(str.encode(data_string+extra*"-"), s)
    elif split_data[0][1:] == "GAGSV":
        # Galileo in view
        data_string = "1389,"+split_data[3]+"\n"
        extra = 0
        if len(data_string) < 80:
            extra = 80-len(data_string)
        send_data(str.encode(data_string+extra*"-"), s)
    elif split_data[0][1:] == "GBGSV":
        # BeiDou in view
        data_string = "1409,"+split_data[3]+"\n"
        extra = 0
        if len(data_string) < 80:
            extra = 80-len(data_string)
        send_data(str.encode(data_string+extra*"-"), s)
    elif split_data[0][3:] == "GGA":
        # full command
        data_string = "0,"+data[1:]
        extra = 0
        if len(data_string) < 80:
            extra = 80-len(data_string)
        send_data(str.encode(data_string+extra*"-"), s)
        # time
        if (split_data[1] != ""):
            data_string ="606,"+split_data[1][:2]+":"+split_data[1][2:4]+":"+split_data[1][4:6]+"\n"
            extra = 0
            if len(data_string) < 80:
                extra = 80-len(data_string)
            send_data(str.encode(data_string+extra*"-"), s)
        # altitude
        if (split_data[9] != ""):
            data_string = "986,"+split_data[9]+"\n"
            extra = 0
            if len(data_string) < 80:
               extra = 80-len(data_string)
            send_data(str.encode(data_string+extra*"-"), s)
    elif split_data[0][3:] == "RMC":
        # full command
        data_string = "80,"+data[1:]
        extra = 0
        if len(data_string) < 80:
            extra = 80-len(data_string)
        send_data(str.encode(data_string+extra*"-"), s)
        # speed in knots
        data_string = "807,"+split_data[7]+"knots"+"\n"
        extra = 0
        if len(data_string) < 80:
            extra = 80-len(data_string)
        send_data(str.encode(data_string+extra*"-"), s)
        # date
        data_string = "566,"+split_data[9]+"\n"
        extra = 0
        if len(data_string) < 80:
            extra = 80-len(data_string)
        send_data(str.encode(data_string+extra*"-"), s)
    elif split_data[0][3:] == "VTG":
        # full command
        data_string = "160,"+data[1:]
        extra = 0
        if len(data_string) < 80:
            extra = 80-len(data_string)
        send_data(str.encode(data_string+extra*"-"), s)
        # speed in km/h
        data_string = "847,"+split_data[7]+"km/h"+"\n"
        extra = 0
        if len(data_string) < 80:
            extra = 80-len(data_string)
        send_data(str.encode(data_string+extra*"-"), s)
    elif split_data[0][3:] == "GLL":
        # full command
        data_string = "240,"+data[1:]
        extra = 0
        if len(data_string) < 80:
            extra = 80-len(data_string)
        send_data(str.encode(data_string+extra*"-"), s)
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
