set PackageName=Core/1.0.0@common/stable
conan create . %PackageName% -pr msvcprofile
conan create . %PackageName% -pr msvcprofiled

@rem conan test CoreTest Core/1.0.0@common/stable -pr msvcprofile
conan upload %PackageName% --all -r=p1
