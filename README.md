rpi_dht
=======

A collection of utilities to log, graph and react to DHT11 sensor data on the Raspberry Pi

Assuming you have WiringPi (https://github.com/WiringPi/WiringPi)

cd src
cmake -G "Unix Makefiles"
make


sudo apt-get install apache2
cp /home/pi/rpi_dht/html/temp.html /var/www/
cp /home/pi/rpi_dht/html/dygraph-combined.js /var/www/

mount a USB stick on /media/usbstick.  I had to do this because the frequent writes to the flash disk caused my first to fail.

ln -s /media/usbstick/exhaust_in.log /var/www/exhaust_in.log
ln -s /media/usbstick/exhaust_out.log /var/www/exhaust_out.log
ln -s /media/usbstick/intake_in.log /var/www/intake_in.log
ln -s /media/usbstick/intake_out.log /var/www/intake_out.log
ln -s /media/usbstick/loft.log /var/www/loft.log


add to cron with
sudo crontab -e

* * * * * echo `date +\%Y\%m\%d\%H\%M\%S`,`/home/pi/rpi_dht/src/dht11 4`  >> /media/usbstick/exhaust_in.log
* * * * * echo `date +\%Y\%m\%d\%H\%M\%S`,`/home/pi/rpi_dht/src/dht11 17` >> /media/usbstick/exhaust_out.log
* * * * * echo `date +\%Y\%m\%d\%H\%M\%S`,`/home/pi/rpi_dht/src/dht11 21` >> /media/usbstick/intake_in.log
* * * * * echo `date +\%Y\%m\%d\%H\%M\%S`,`/home/pi/rpi_dht/src/dht11 22` >> /media/usbstick/intake_out.log
* * * * * echo `date +\%Y\%m\%d\%H\%M\%S`,`/home/pi/rpi_dht/src/dht11 25` >> /media/usbstick/loft.log

sudo service cron start
sudo update-rc.d cron defaults


