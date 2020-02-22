function Component()
{
	var programFiles = installer.environmentVariable("ProgramFiles");
	
	if (programFiles !== "")
	{
		programFiles = programFiles.replace(" (x86)", "")
	
		installer.setValue("TargetDir", programFiles + "\\Qvs");
	}
	
	installer.setDefaultPageVisible(QInstaller.ComponentSelection, false);
	installer.setDefaultPageVisible(QInstaller.StartMenuSelection, false);
}
