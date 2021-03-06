# DBDrives
Manage HDD/SSD information
* vendor
* model number
* serial number
* warranty expires

## Environment
* Microsoft Windows 10 (needs administrator privileges)
* Microsoft Visual Studio 2019 (C++17, MFC)
* Oracle Database 18c (ODBC)
* Oracle Instant Client 19.5

## Registry setting
```
[HKEY_CURRENT_USER\Software\mahori\DBDrives\Database]
"ConnectString"="ODBC;DRIVER={Oracle in Oracle};DSN=[DataSourceName];UID=[UserID];PWD=[Password]"
```

## Create database [Oracle Database 18c]
```SQL
CREATE TABLE DRIVES (
  ID               INTEGER GENERATED BY DEFAULT AS IDENTITY,
  VENDOR           VARCHAR2(32),
  MODEL_NUMBER     VARCHAR2(32),
  SERIAL_NUMBER    VARCHAR2(32),
  WARRANTY_EXPIRES DATE
  );
```

## License

### MIT
`AtaSmart.{cpp,h}`, `DnpService.h`, `GetOsInfo.h`, `NVMeInterpreter.{cpp,h}`, `SlotSpeedGetter.{cpp,h}`, `SPTIUtil.h`, `StorageQuery.h`

### BSD 2-Clause
Others

## Acknowledgments
ひよひよ氏 : [CrystalDiskInfo](https://crystalmark.info/ja/software/crystaldiskinfo/)
