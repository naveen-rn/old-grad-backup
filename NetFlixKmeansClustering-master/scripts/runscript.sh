#!/bin/bash

echo "Beginning output_step1"

if [ -d output_step1/ ]; then rm -rf output_step1/; fi

yarn jar build/lib/NetFlix.jar examples.NetFlixAnalysisDataAggregate input/ output_step1/

echo "End output_step1"

echo "Beginning output_step2"

if [ -d output_step2/ ]; then rm -rf output_step2/; fi

yarn jar build/lib/NetFlix.jar examples.NetFlixAnalysisCanopyData output_step1/ output_step2/

echo "End output_step2"

echo "Beginning output_step3"

if [ -d output_step3/ ]; then rm -rf output_step3/; fi

yarn jar build/lib/NetFlix.jar examples.NetFlixAnalysisCanopyMovies output_step1/ output_step3/

echo "End output_step3"
