native_stub:
	cmake -S stub -B build/ -G Ninja; cmake --build build


dev:
	moon build --target native; ./target/native/release/build/qpainter.exe


run: 
	./target/native/release/build/qpainter.exe