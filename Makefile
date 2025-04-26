native_stub:
	cmake -S stub -B build/ -G Ninja; cmake --build build


fmt:
	moon fmt; moon info --target native;