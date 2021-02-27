import serial
import socket

HOST = "0.0.0.0"  # Standard loopback interface address (localhost)
PORT = 8082  # Port to listen on (non-privileged ports are > 1023)


def send_data(data, s):
    print(data)
    s.sendall(data)
    return


def parse_data(data, s):
    split_data = data.split(",")
    if split_data[0][1:] == "GNGSV":
        # Any combo satelites in view
        send_data(str.encode("1349," + split_data[3]), s)
    elif split_data[0][1:] == "GLGSV":
        # GLONASS in view
        send_data(str.encode("1289," + split_data[3]), s)
    elif split_data[0][1:] == "GAGSV":
        # Galileo in view
        send_data(str.encode("1309," + split_data[3]), s)
    elif split_data[0][1:] == "GBGSV":
        # BeiDou in view
        send_data(str.encode("1329," + split_data[3]), s)
    elif split_data[0][3:] == "GGA":
        # full command
        send_data(str.encode("0," + data[1:]), s)
        # time
        send_data(
            str.encode(
                "606,"
                + split_data[1][:2]
                + ":"
                + split_data[1][2:4]
                + ":"
                + split_data[1][4:6]
            ),
            s,
        )
        # altitude
        send_data(str.encode("906," + split_data[9]), s)
    elif split_data[0][3:] == "RMC":
        # full command
        send_data(str.encode("80," + data[1:]), s)
        # speed in knots
        send_data(str.encode("727," + split_data[7] + " knots"), s)
    elif split_data[0][3:] == "VTG":
        # full command
        send_data(str.encode("160," + data[1:]), s)
        # speed in km/h
        send_data(str.encode("767," + split_data[7] + " km/h"), s)
    elif split_data[0][3:] == "GLL":
        # full command
        send_data(str.encode("240," + data[1:]), s)
    else:
        return


# Open serial port
ser = serial.Serial(
    port="COM7", baudrate=9600, bytesize=8, timeout=2, stopbits=serial.STOPBITS_ONE
)

# open client
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((HOST, PORT))

while 1:

    # Wait until there is data waiting in the serial buffer
    if ser.in_waiting > 0:
        # Read data from buffer
        serialString = ser.readline()
        # Decode to ASCII
        data = serialString.decode("Ascii")
        # Parse data
        parse_data(data, s)
