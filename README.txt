OBJECT DUMP, built by GitHub (no tools to install)
===================================================
1. Unzip this zip. You should have a folder with: mod.json, CMakeLists.txt, a "src" folder
   and a ".github" folder.
2. Make a free GitHub account if you don't have one (github.com), then click "+" > "New repository".
   Name it  gd-object-dump , keep it Private or Public, click "Create repository".
3. On the new empty repository page click "uploading an existing file".
   Drag EVERYTHING from inside the unzipped folder into the page (mod.json, CMakeLists.txt, src, .github).
   Check the file list shows  .github/workflows/build.yml  and  src/main.cpp , then click "Commit changes".
4. Click the "Actions" tab. A run called "Build Geode Mod" starts by itself. Wait until it has a green tick
   (a few minutes). Red cross = build error: click it, copy the red error text and send it to me.
5. Open the finished run, scroll to "Artifacts", download "Build Output" (a zip), open it, and take the file
   that ends in  .geode
6. Put that .geode file in:   D:\SteamLibrary\steamapps\common\Geometry Dash\geode\mods
7. Start Geometry Dash and wait at the main menu. After a few seconds of freezing a popup says
   "Object Dump finished" and shows where objects.jsonl was saved. Send me that file.
   If GD crashes while dumping, just start it again: it resumes and skips the object that crashed.
8. Afterwards disable or delete the mod in Geode's mod list.
