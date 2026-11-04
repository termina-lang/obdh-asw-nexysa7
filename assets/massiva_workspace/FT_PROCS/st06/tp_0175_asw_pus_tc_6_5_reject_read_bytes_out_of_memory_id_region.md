
# TP_0175_ASW_PUS_TC_6_5_REJECT_READ_BYTES_OUT_OF_MEMORY_ID_REGION

The test checks that telecommand TC(6,5) whose start address lies outside the
region of its memory ID (address of bank 0 with memory ID 1) is effectively
rejected and the TM (1,1) and TM (1,4) are received with error code 8.

| STEPS | | | | |
|-------|-|-|-|-|
| **TO + 1** | **STEP0** | | | |
| | | **INPUTS** | **TC** | **App Data** |
| | Send the TC (6,5) with an address out of the region of its memory ID | | TC(6,5) | N = 1, Memory ID = 1, Start Address = 0x40001000, Length = 0x10 |
| | | **OUTPUTS** | **TM** | **App Data Filter** |
| | Check that the telecommand is rejected and the TM (1,1) and TM (1,4) telemetry packets are received with error code 8 | | TM(1,1)<br>TM(1,4) | Error Code = 8, Memory ID = 0x01, Start Address = 0x40001000 |
