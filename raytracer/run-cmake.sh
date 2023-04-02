#!/usr/bin/env bash

mkdir -p release
mkdir -p debug
mkdir -p testing


(cd release; cmake -DCMAKE_BUILD_TYPE=Release ../raytracer)
(cd debug; cmake -DCMAKE_BUILD_TYPE=Debug ../raytracer)
(cd testing; cmake -DCMAKE_BUILD_TYPE=Testing ../raytracer)