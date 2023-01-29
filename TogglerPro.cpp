#include <iostream>
#include <windows.h>
#include <vector>

int main() {
  // Get the current display settings
  DEVMODE devmode;
  EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &devmode);

  std::vector<int> refresh;
  std::vector<int> wid;
  std::vector<int> heigh;

  // Print a list of available refresh rates and resolutions
  printf("Available refresh rates and resolutions:\n");
  for (int i = 0; EnumDisplaySettings(NULL, i, &devmode) != 0; i++) {
    if (devmode.dmFields & DM_DISPLAYFREQUENCY) {
      std::cout << i << " - " << devmode.dmPelsWidth << " x " << devmode.dmPelsHeight << " @ " << devmode.dmDisplayFrequency << " Hz" << std::endl;
      wid.push_back(devmode.dmPelsWidth);
      heigh.push_back(devmode.dmPelsHeight);
      refresh.push_back(devmode.dmDisplayFrequency);
    }
  }

  // Prompt the user to enter a refresh rate and resolution option
  int rate, width, height, option = -1;
  std::cout << std::endl;
  while (option < 0 or option >= wid.size())
  {
    std::cout << "Enter a Valid Desired Option: ";
    std::cin >> option;
  }
  std::cout << std::endl;
  // It then chooses the option
  rate = refresh[option];
  width = wid[option];
  height = heigh[option];

  // Set the selected refresh rate and resolution
  devmode.dmDisplayFrequency = rate;
  devmode.dmPelsWidth = width;
  devmode.dmPelsHeight = height;

  // Save the changes to the display settings
  ChangeDisplaySettingsEx(NULL, &devmode, NULL, CDS_UPDATEREGISTRY, NULL);

  std::cout << "Your refresh rate has been changed to " << devmode.dmDisplayFrequency << "Hz" << std::endl;
  std::cout << "Your resolution has been changed to " << devmode.dmPelsWidth << " x " << devmode.dmPelsHeight << std::endl;
  return 0;
}