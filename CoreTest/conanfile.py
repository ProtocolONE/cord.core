from conans import ConanFile, MSBuild, tools
import os

class CoreConan(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "visual_studio"
    options = {"shared": [True, False]}

    def build(self):

        customBuildType = self.settings.get_safe("build_type")
        if self.options.shared == "False":
          customBuildType = 'Static {0}'.format(customBuildType)
          
        print('Custom build: ' + customBuildType)
        print('CurrentDir: ' + os.getcwd())
    
        msbuild = MSBuild(self)
        msbuild.build(
        "../../CoreTest.vcxproj"
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

    def imports(self):
        self.copy("*.dll", dst="bin", src="bin")
        self.copy("*.dylib*", dst="bin", src="lib")
        self.copy('*.so*', dst='bin', src='lib')

    def test(self):
        customBuildType = self.settings.get_safe("build_type")
        if self.options.shared == "False":
          customBuildType = 'Static {0}'.format(customBuildType)

        #if not tools.cross_building(self.settings):
        os.chdir("../../!Build/CoreTest/{0}".format(customBuildType))
        self.run("CoreTest.exe")
