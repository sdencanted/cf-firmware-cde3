# cf-firmware
firmware for AFC CDE3
## Changes in this fork
- added the ability to sing(MotorsBeep)
- added the ability to reset the estop
- not sure what the original changes are prior to this fork, the original custom firmware was made for [SUTD AFC CDE3](https://github.com/sdencanted/crazyflie-clients-python-cde3) using the Crazyflie 2.1 and the flow 2.0 deck
### Example in python cflib(no custom version of cflib needed)
```python
from cflib.crtp.crtpstack import CRTPPacket
from cflib.crtp.crtpstack import CRTPPort
import struct


estop_reset_pk = CRTPPacket()
estop_reset_pk.port = CRTPPort.LOCALIZATION
estop_reset_pk.channel =  GENERIC_CH = 1
estop_reset_enum=5
estop_reset_pk.data = struct.pack('<BB',
                    estop_reset_enum,estop_reset_enum)



sing_pk = CRTPPacket()
sing_pk.port = CRTP_PORT_SING=9
# pack time and freq as uint16_t to struct
# time in milliseconds, then freq of each propeller
sing_pk.data=struct.pack('<5H', 1000,440, 440, 440, 440)

uris= {"radio://0/30/2M/E7E7E7E7E7","radio://0/30/2M/E7E7E7E701"}
cflib.crtp.init_drivers()
with Swarm(uris, factory= CachedCfFactory(rw_cache='./cache')) as swarm:
    for cf in swarm.all_cfs:
        cf = scf.cf
        cf.send_packet(estop_reset_pk)

        cf.send_packet(sing_pk)
```