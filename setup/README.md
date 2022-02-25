Usage
===
1. Copy all files to `.\qvs\` dir.

2. Run `app_package.bat` for create qvs portable 7z file.
3. Run `app_setup.bat` for create qvs setup exe file.



# When Released

Should edit follow files.

`setup\config.xml`

```xml
<?xml version="1.0" encoding="UTF-8"?>
<Installer>
    <Name>Qvs</Name>
    <Version>r17.2</Version>
    <Title>Qvs</Title>
    <Publisher>ema</Publisher>
    <StartMenuDir>Qvs</StartMenuDir>
    <AllowNonAsciiCharacters>true</AllowNonAsciiCharacters>
    <TargetDir>@HomeDir@/qvs</TargetDir>
	<AdminTargetDir>@RootDir@/qvs</AdminTargetDir>
	<MaintenanceToolName>qvs-maintenance-tool</MaintenanceToolName>
</Installer>
```

`setup\packages\noumenon\meta\package.xml`

```xml
<?xml version="1.0" encoding="UTF-8"?>
<Package>
    <DisplayName>Qvs</DisplayName>
    <Description>Qvs program.</Description>
    <Version>0.17.2</Version>
    <ReleaseDate>2022-02-02</ReleaseDate>
    <Default>true</Default>
    <Script>installscript.qs</Script>
</Package>
```

`com\version.h`

```c++
#ifndef VERSION_H
#define VERSION_H

#define QVS_VERSION "r17.2"

#endif // VERSION_H
```

