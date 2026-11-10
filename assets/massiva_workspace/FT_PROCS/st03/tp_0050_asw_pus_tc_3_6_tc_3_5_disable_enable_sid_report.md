
# TP_0050_ASW_PUS_TC_3_6_TC_3_5_DISABLE_ENABLE_SID_REPORT

The test checks that telecommand TC(3,6) to disable SID report and TC(3,5) to
enable SID report are executed correctly and the appropriate TM responses are
received.

| STEPS | | | | |
|-------|-|-|-|-|
| **TO + 1** | **STEP0** | | | |
| | | **INPUTS** | **TC** | **App Data** |
| | Send the TC (3,6) to disable SID 0 report | | TC(3,6) | SID = 0 |
| | | **OUTPUTS** | **TM** | **App Data Filter** |
| | Check that the received sequence is TM (1,1), TM (1,3), TM (1,7)<br>Check that no telemetry from SID 0 is received until it is enabled again | | TM(1,1)<br>TM(1,3)<br>TM(1,7) | |
| **TO + 100** | **STEP1** | | | |
| | | **INPUTS** | **TC** | **App Data** |
| | Send the TC (3,5) to enable SID 0 report | | TC(3,5) | SID = 0 |
| | | **OUTPUTS** | **TM** | **App Data Filter** |
| | Check that the received sequence is TM (1,1), TM (1,3), TM (1,7) | | TM(1,1)<br>TM(1,3)<br>TM(1,7) | |
