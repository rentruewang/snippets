INPUT := input
OUTPUT := output
REMOTE := "http://hpc.ee.ntu.edu.tw/html/IntelligentClouds/webAccessLog/access_log"
LOCAL := $(INPUT)/access_log

STREAMING := $(shell echo $$HOME/.local/hadoop-3.3.0/share/hadoop/tools/lib/hadoop-streaming-3.3.0.jar)
STREAMING_MAPPER := ./streaming/mapper.py
STREAMING_REDUCER := ./streaming/reducer.py

JAR := ./native/build/libs/nativ.jar

STREAMING_ARGS = -input $(INPUT) -output $(OUTPUT) -mapper "python $(STREAMING_MAPPER)" -reducer "python $(STREAMING_REDUCER)"


all: clean wget

build_jar: 
	bash -c  "cd native && ./gradlew build"

jar: all build_jar
	hadoop jar $(JAR) $(INPUT) $(OUTPUT)

streaming: all
	hadoop jar $(STREAMING) $(STREAMING_ARGS)
		
wget:
	$(shell test -f $(LOCAL) || wget $(REMOTE) -O- > $(LOCAL))

clean: 
	$(shell mkdir -p $(INPUT))
	$(shell rm -rf $(OUTPUT))
