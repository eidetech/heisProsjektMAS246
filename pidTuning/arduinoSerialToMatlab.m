% Connect to serial port and set properties
serial1 = serial('/dev/ttyS0', 'BaudRate', 9600);
fopen(serial1);
while 1
    % Get 2 bytes of data from each device
    data1 = fread(serial1, 10);
    data2 = fread(serial1, 10);
    
    % Print the data
    fprintf("Data1: %d \t Data2: %d\n",data1,data2)
end
% Close connection(s)
fclose(serial1);
delete(serial1)
clear serial1