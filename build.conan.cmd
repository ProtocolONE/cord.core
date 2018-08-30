conan create . Core/1.0.0@common/stable -pr msvcprofile
conan test CoreTest Core/1.0.0@common/stable -pr msvcprofile
