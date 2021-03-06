# Simple-ATM-Controller
Coding Assessment

![Ubuntu](https://github.com/prajankya/Simple-ATM-Controller/workflows/Ubuntu/badge.svg)

![Demo SVG](https://raw.githubusercontent.com/prajankya/Simple-ATM-Controller/main/demo.svg)


## Documentation

Full Project documentation can be found at

https://prajankya.github.io/Simple-ATM-Controller/

The main class developed for this assessment is documented at

https://prajankya.github.io/Simple-ATM-Controller/classATMController.html


## Installing

**Step 1:** Requirements

- g++ >= 7 (on Linux)
- clang >= 3.1 (on MacOSX)
- cmake >= 3.5.1
- doxygen >= 1.8
- git

For Ubuntu
```shell
sudo apt install g++ cmake doxygen git
```

For Mac OSX
```shell
brew install cmake doxygen git
```

**Step 2:** Downloading the source
```shell
git clone https://github.com/prajankya/Simple-ATM-Controller
```

**Step 3:** Compiling

```shell
cd Simple-ATM-Controller
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug ..
make
```



## Running
You can run a sample program which uses ATMController.

Run the following command from inside the build folder:
```shell
./src/ATMController
```

This sample program allows user to enter wrong input/ go in wrong state to allow them to test ATMController more effectively.



## Testing
Run the following command from inside the build folder:
```shell
ctest
```

![Test SVG](https://raw.githubusercontent.com/prajankya/Simple-ATM-Controller/main/test.svg)


## Developing

ATMController uses STATE machine to manage a complete transaction by user. An ATM can take in one card at a time. Hence a function called `EjectCard()` can be used to remove existing and insert a new card.

Few key points considered while developing this project
- Developing Bank API is out of the scope of this project but a basic API is provided in "supporting_classes".
- The basic Bank API is developed to be `stateless` and hence, ATMController is supposed to save all transactional details and send them on every call.
- ATMController contains card and pin validation which may be similar to that inside Bank API, but internal validation in Bank API is out of the scope.
