from conans import ConanFile, MSBuild, VisualStudioBuildEnvironment, tools
from conans.util.files import tmp_file
import re

componentName = "Core"

class CoreConan(ConanFile):
    name = componentName
#    version = "1.0"
    license = "<Put the package license here>"
    url = "<Package recipe repository url here, for issues about the package>"
    description = "<Description of Core here>"
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False]}
    default_options = "shared=False"
    generators = "visual_studio_multi"
    requires = "Qt/5.5.1@common/stable"
    build_requires = "Qt/5.5.1@common/stable"
    
    scm = {
      "type": "git",
      "url": "auto",
      "revision": "auto"
    }
    
    def build(self):
      self.output.warn('Using Qt: conan-{0}'.format(self.info.requires["Qt"].full_package_id))
      # content = tools.load("Core\\Core.vcxproj")
      # content = re.sub(r'Qt5Version_x0020_Win32=\".+?\"', r'Qt5Version_x0020_Win32="conan-{0}"'.format(self.info.requires["Qt"].full_package_id), content)
      # tools.save("Core/Core.vcxproj", content)

      if self.options.shared == "False":
        tools.replace_in_file("{0}/{0}.vcxproj".format(componentName), "<ConfigurationType>DynamicLibrary</ConfigurationType>", "<ConfigurationType>StaticLibrary</ConfigurationType>")

      libMap = {
        "x86" : "MachineX86"
        ,'x86_64' : 'MachineX64'
      }

      arch = self.settings.get_safe("arch")
      
      props_file_contents = """<?xml version="1.0" encoding="utf-8"?>
<Project xmlns="http://schemas.microsoft.com/developer/msbuild/2003">
  <ItemDefinitionGroup>
    <Lib>
      <TargetMachine>{0}</TargetMachine>
    </Lib>
  </ItemDefinitionGroup>
</Project>""".format(libMap[arch])

      with tmp_file(props_file_contents) as props_file_path:
        msbuild = MSBuild(self)
        msbuild.build(
        "{0}/{0}.vcxproj".format(componentName)
         , toolset = self.settings.compiler.toolset
         , platforms={ 
            "x86" : "Win32"
            ,'x86_64' : 'x64'
          }
          ,
          properties = {
            "ForceImportBeforeCppTargets" : props_file_path
          }
        )

    def package(self):
        self.copy("*", dst="include", src="{0}/include".format(componentName))
        self.copy("*.ts", dst="i18n", keep_path=False)
        self.copy("*.lib", dst="lib", keep_path=False)
        self.copy("*.dll", dst="bin", keep_path=False)
        self.copy("*.dylib*", dst="lib", keep_path=False)
        self.copy("*.so", dst="lib", keep_path=False)
        self.copy("*.a", dst="lib", keep_path=False)

    #def imports(self):        
       #self.copy("*.dll", "Core/!build/", "bin")

    def package_info(self):
      name = componentName
      if self.settings.arch == "x86":
        name += "x86"
        
      if self.settings.arch == "x86_64":
        name += "x64"
        
      if self.settings.build_type == "Debug":
        name += "d"

      name += ".lib"
      self.cpp_info.libs = [name] # The libs to link against
      
      
      self.cpp_info.includedirs = ['include']  # Ordered list of include paths
      self.cpp_info.libdirs = ['lib']  # Directories where libraries can be found
      self.cpp_info.resdirs = ['res']  # Directories where resources, data, etc can be found
      self.cpp_info.bindirs = ['bin']  # Directories where executables and shared libs can be found
      self.cpp_info.defines = []  # preprocessor definitions
      self.cpp_info.cflags = []  # pure C flags
      self.cpp_info.cppflags = []  # C++ compilation flags
      self.cpp_info.sharedlinkflags = []  # linker flags
      self.cpp_info.exelinkflags = []  # linker flags
      
      if self.options.shared == "False":
        self.cpp_info.defines.append("{0}_STATIC_LIB".format(componentName.upper()))

      

      
