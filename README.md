# Painting-For-Kids
Paint for Kids - A C++ OOP project that helps kids draw, color, move, and play with shapes in a simple GUI. It supports drawing and play modes, with save/load and undo/redo features

👉 **How to use the program (guide for kids): [HOW_TO_USE.md](HOW_TO_USE.md)**

## Requirements

- Windows 10 or 11
- Visual Studio 2022 (Community) **or** Visual Studio 2022 Build Tools, with the **Desktop development with C++** workload (MSVC v143 + Windows SDK)

To install only the build tools from PowerShell:

```powershell
winget install --id Microsoft.VisualStudio.2022.BuildTools --exact --override "--wait --passive --norestart --add Microsoft.VisualStudio.Workload.VCTools --includeRecommended"
```

## Build

Run in PowerShell from the repository folder:

```powershell
cd "Paint For Kids Project"

# find MSBuild (works for Visual Studio and Build Tools)
$msbuild = & "${env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe" -latest -products * -requires Microsoft.Component.MSBuild -find "MSBuild\**\Bin\MSBuild.exe"

# Release build (optimized, use this to play)
& $msbuild PT-Project.sln /p:Configuration=Release /p:Platform=Win32

# Debug build (for development)
& $msbuild PT-Project.sln /p:Configuration=Debug /p:Platform=Win32
```

If you changed a class (for example added a virtual function) and get strange crashes, do a full rebuild:

```powershell
& $msbuild PT-Project.sln /t:Rebuild /p:Configuration=Release /p:Platform=Win32
```

## Run

Run from inside the `Paint For Kids Project` folder, so the program finds the `images` folder and the `.wav` sounds:

```powershell
cd "Paint For Kids Project"
& ".\Release\PT Project.exe"
```

Debug build:

```powershell
& ".\Debug\PT Project.exe"
```

In the Debug build every runtime error is also written with its call stack (function, file and line) to `debug_log.txt` in the `Paint For Kids Project` folder.

## Using Visual Studio

Open `Paint For Kids Project\PT-Project.sln`, choose **Release** and **x86** in the toolbar, then press **Ctrl+F5**.

## Save files

**Save** asks for a file name and writes `<name>.txt` in the `Paint For Kids Project` folder. **Load** reads the same file back (press **Esc** to cancel).
