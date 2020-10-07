#define _CRT_SECURE_NO_WARNINGS

#include "Windows.h"
#include <atlstr.h>
#include <vector>
#include <fstream>
#include <string>
#include <filesystem>

using namespace std;

const string rate = "104857600";

#define filepath filesystem::path

#define towide wstring().c_str

BOOL ReadIniFile(filepath path, vector<string>& fileContents)
{
	BOOL isOk = TRUE;
	ifstream iFile;

	fileContents.clear();

	iFile.open(path);

	string str;
	if (iFile.is_open()) 
	{
		while (getline(iFile, str)) 
		{
			fileContents.push_back(str);
		} 
	}
	else
	{
		CString cStr;
		cStr = L"Error reading from path ";
		cStr += path.towide();
		MessageBox(NULL, cStr, L"Error", MB_ICONERROR);
		isOk = FALSE;
	}

	iFile.close();

	return isOk;
}

BOOL WriteIniFile(filepath path, vector<string>& fileContents)
{
	BOOL isOk = TRUE;

	ofstream oFile;

	oFile.open(path);

	if (oFile.is_open())
	{
		for (auto it = fileContents.begin(); it != fileContents.end(); it++)
		{
			string toWrite = *it;
			toWrite += "\n";
			oFile.write(toWrite.c_str(), toWrite.length());
		}
	}
	else
	{
		CString cStr;
		cStr = L"Error writing to path ";
		cStr += path.towide();
		MessageBox(NULL, cStr, L"Error", MB_ICONERROR);
		isOk = FALSE;
	}

	oFile.close();

	return isOk;
}

void SetVariable(vector<string>& fileContents, string variable, string value)
{
	BOOL isFound = FALSE;
	
	string setString = variable;
	if (!value.empty())
	{
		setString += "=";
		setString += value;
	}

	for (auto it = fileContents.begin(); it != fileContents.end(); it++)
	{
		if (it->find(variable) != string::npos)
		{
			*it = setString;
			isFound = TRUE;
		}
	}

	if (isFound == FALSE)
	{
		fileContents.push_back(setString);
	}
}

BOOL MakeReadable(CString cStr)
{
	return SetFileAttributes(cStr, GetFileAttributes(cStr) & ~FILE_ATTRIBUTE_READONLY);
}

BOOL MakeReadOnly(CString cStr)
{
	return SetFileAttributes(cStr, GetFileAttributes(cStr) | FILE_ATTRIBUTE_READONLY);
}

int main()
{
	BOOL isOk = TRUE;

	if (MessageBoxW(NULL, L"This application will make changes to Satisfactory's .ini files to fix the lag issue.\nSee the README file for details.\n\nContinue?", L"Satisfactory Lag Fix", MB_ICONQUESTION | MB_YESNO) == IDYES)
	{
		filepath appData = _wgetenv(L"localappdata");

		filepath folder = appData;
		folder /= "FactoryGame\\Saved\\Config\\WindowsNoEditor\\";

		filepath path;
		filepath copyPath;
		vector<string> fileContents;

		//Engine.ini
		path = folder;
		path += "Engine.ini";
		MakeReadable(path.towide());

		copyPath = path;
		copyPath.replace_filename("_Engine");
		copyPath.replace_extension(".ini.bak");
		CopyFileW(path.wstring().c_str(), copyPath.wstring().c_str(), TRUE);
		ReadIniFile(path, fileContents);

		SetVariable(fileContents, "ConfiguredInternetSpeed", rate);
		SetVariable(fileContents, "ConfiguredLanSpeed", rate);
		SetVariable(fileContents, "MaxClientRate", rate);
		SetVariable(fileContents, "MaxInternetClientRate", rate);

		isOk &= WriteIniFile(path, fileContents);

		isOk &= MakeReadOnly(path.towide());

		//Game.ini
		path = folder;
		path += "Game.ini";
		MakeReadable(path.towide());
		copyPath = path;
		copyPath.replace_filename("_Game");
		copyPath.replace_extension(".ini.bak");
		CopyFileW(path.wstring().c_str(), copyPath.wstring().c_str(), TRUE);
		ReadIniFile(path, fileContents);

		SetVariable(fileContents, "TotalNetBandwidth", rate);
		SetVariable(fileContents, "MaxDynamicBandwidth", rate);
		SetVariable(fileContents, "MinDynamicBandwidth", rate);

		isOk &= WriteIniFile(path, fileContents);
		isOk &= MakeReadOnly(path.towide());

		//Scalability.ini
		path = folder;
		path += "Scalability.ini";
		MakeReadable(path.towide());

		copyPath = path;
		copyPath.replace_filename("_Scalability");
		copyPath.replace_extension(".ini.bak");
		CopyFileW(path.wstring().c_str(), copyPath.wstring().c_str(), TRUE);
		ReadIniFile(path, fileContents);

		SetVariable(fileContents, "[NetworkQuality@3]", "");
		SetVariable(fileContents, "TotalNetBandwidth", rate);
		SetVariable(fileContents, "MaxDynamicBandwidth", rate);
		SetVariable(fileContents, "MinDynamicBandwidth", rate);

		isOk &= WriteIniFile(path, fileContents);

		isOk &= MakeReadOnly(path.towide());

		if (isOk)
		{
			MessageBoxW(NULL, L"Fixes successfully applied.\n\n"
				"For the changes to take effect, please ensure that Network Quality is set to Ultra:\n\n"
				"1) While in game, go to Options -> Gameplay.\n"
				"2) Switch Network Quality to Ultra and click Apply.\n", L"Satisfactory Lag Fix", MB_ICONINFORMATION);
		}
	}
}