set PackageName=Core/1.0.0@common/stable

@call install.deps.cmd

conan create . %PackageName% -pr msvcprofile
conan create . %PackageName% -pr msvcprofiled

conan upload %PackageName% --all -r=p1
