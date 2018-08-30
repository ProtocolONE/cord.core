from conans import ConanFile, MSBuild


class CoreConan(ConanFile):
    name = "Core"
#    version = "1.0"
    license = "<Put the package license here>"
    url = "<Package recipe repository url here, for issues about the package>"
    description = "<Description of Core here>"
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False]}
#    default_options = "shared=False"
    generators = "visual_studio"
#    exports_sources = "!../Core/GeneratedFiles/*","!../CoreTest/GeneratedFiles/*", "!../!build/*", "!../!obj/*", "!../.vs/*", "!../.git/*","../*"

    scm = {
      "type": "git",
      "url": "auto",
      "revision": "auto"
    }
    
    def build(self):
        customBuildType = self.settings.get_safe("build_type")
        if self.options.shared == "False":
          customBuildType = 'Static {0}'.format(customBuildType)
          
        print('Custom build: ' + customBuildType)
    
        msbuild = MSBuild(self)
        msbuild.build(
        "Core/Core.vcxproj"
        #"Core.sln"
         , build_type = customBuildType
         , platforms={ 
            "x86" : "Win32"
            ,'x86_64' : 'x64'
          }
          , properties={
            "CommonArea" : "trunk"
          }
        )

    def package(self):
        self.copy("*", dst="include", src="Core/include")
        self.copy("*.lib", dst="lib", keep_path=False)
        self.copy("*.dll", dst="bin", keep_path=False)
        self.copy("*.dylib*", dst="lib", keep_path=False)
        self.copy("*.so", dst="lib", keep_path=False)
        self.copy("*.a", dst="lib", keep_path=False)

    def package_info(self):
        self.cpp_info.libs = ["Core"]
