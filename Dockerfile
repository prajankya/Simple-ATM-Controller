FROM debian:stable-slim

RUN apt-get update -y && \
	apt-get install -y --no-install-recommends \
	git \
	openssh-server \
	curl \
	gcc \
	g++ \
	build-essential \
	cmake \
	doxygen \
	sudo \
	python3 \
	python3-defusedxml \
	python3-lxml \
	libssl-dev \
	libffi-dev \
	ca-certificates && \
	apt-get autoclean && \
	apt-get autoremove && \
	apt-get clean && \
	rm -rf /var/lib/apt/lists/*

# Copy the current folder which contains C++ source code to the Docker image under /usr/src
COPY . /usr/src/simple_atm_controller

# Specify the working directory
WORKDIR /usr/src/simple_atm_controller

# Remove build if it exists &
# Compile in debug mode
RUN rm -rf /usr/src/simple_atm_controller/build && \
	cmake -DCMAKE_BUILD_TYPE=Debug . && \
	make

# Run the output program from the previous step
CMD ["cmake", "--build", ".", "--target", "test"]