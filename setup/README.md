Usage
===
1. Copy all files to `.\qvs\` dir.

2. Run `app_installer.bat` for create qvs installer exe file.
3. Run `app_package.bat` for create qvs portable 7z file.



# When Released

Should edit follow files.

`config.xml`

```xml
<?xml version="1.0" encoding="UTF-8"?>
<Installer>
    <Name>Qvs</Name>
    <Version>r17</Version>
    <Title>Qvs</Title>
    <Publisher>ema</Publisher>
    <StartMenuDir>Qvs</StartMenuDir>
    <AllowNonAsciiCharacters>true</AllowNonAsciiCharacters>
    <TargetDir>@HomeDir@/qvs</TargetDir>
	<AdminTargetDir>@RootDir@/qvs</AdminTargetDir>
	<MaintenanceToolName>qvs-maintenance-tool</MaintenanceToolName>
</Installer>
```

`packages\noumenon\meta\package.xml`

```xml
<?xml version="1.0" encoding="UTF-8"?>
<Package>
    <DisplayName>Qvs</DisplayName>
    <Description>Qvs program.</Description>
    <Version>0.17.0</Version>
    <ReleaseDate>2021-12-12</ReleaseDate>
    <Default>true</Default>
    <Script>installscript.qs</Script>
</Package>
```

