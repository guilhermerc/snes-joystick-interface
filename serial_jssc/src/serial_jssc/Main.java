package serial_jssc;

import jssc.SerialPort;
import jssc.SerialPortException;

public class Main {

	public static void main(String[] args) {
		SerialPort serialPort = new SerialPort("/dev/ttyACM0");
		try {
			System.out.println("Port opened: " + serialPort.openPort());
			System.out.println("Params setted: " + serialPort.setParams(9600, 8, 1, 0));
			serialPort.purgePort(SerialPort.PURGE_RXCLEAR);
			while(serialPort.getInputBufferBytesCount() >= 0) {
				System.out.println("Port reading: " + (char) serialPort.readBytes(1)[0]);
			}
			//System.out.println("\"Hello World!!!\" successfully writen to port: " + serialPort.writeBytes("Hello World!!!".getBytes()));
			System.out.println("Port closed: " + serialPort.closePort());
		}
		catch (SerialPortException ex){
			System.out.println(ex);
		}
	}

}