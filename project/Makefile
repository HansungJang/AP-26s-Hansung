VSDEV_TOOLS ?= C:\Program Files (x86)\Microsoft Visual Studio\18\BuildTools\Common7\Tools
MSVC = powershell -NoProfile -Command "$$ErrorActionPreference = 'Stop'; Import-Module '$(VSDEV_TOOLS)\Microsoft.VisualStudio.DevShell.dll'; Enter-VsDevShell -VsInstallPath '$(VSDEV_TOOLS)\..\..' -DevCmdArguments '-arch=amd64 -host_arch=amd64' -SkipAutomaticLocation | Out-Null; & cl.exe
CXXFLAGS = /nologo /W4 /EHsc /std:c++17 /O2

TARGET = holydiver.exe
SRCS = holydiver.cpp Enemy.cpp Player.cpp World.cpp GameManager.cpp Item.cpp
OBJS = $(SRCS:.cpp=.obj)
HEADERS = Enemy.hpp GameManager.hpp Player.hpp World.hpp Item.hpp

.PHONY: all play clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(MSVC) /nologo $(OBJS) /Fe$@; exit $$LASTEXITCODE"

%.obj: %.cpp $(HEADERS)
	$(MSVC) $(CXXFLAGS) /c $< /Fo$@; exit $$LASTEXITCODE"

play: $(TARGET)
	.\$(TARGET)

clean:
	powershell -NoProfile -Command "foreach ($$file in '$(TARGET)', '$(basename $(TARGET)).ilk', '$(basename $(TARGET)).pdb', 'holydiver.obj', 'Enemy.obj', 'Player.obj', 'World.obj', 'GameManager.obj') { if (Test-Path -LiteralPath $$file -PathType Leaf) { Remove-Item -LiteralPath $$file -Force } }"
