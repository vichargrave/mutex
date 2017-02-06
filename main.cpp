/*
   main.cpp

   Test application for the mutex class in C++.
  
   ------------------------------------------

   Copyright (c) 2013 Vic Hargrave - http://vichargrave.com

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "thread.h"
#include "mutex.h"
 
class MutexTest : public Thread
{
    Mutex &m_mutex;
    
    public:
    MutexTest(Mutex& mutex) : m_mutex(mutex) {}
    void* run() {
        printf("thread waiting to get mutex\n");
        m_mutex.lock();
        printf("thread got mutex lock\n");
        // hold lock for awhile to make main thread wait
        sleep(10);
        m_mutex.unlock();
        return NULL;
    }
};

int main(int argc, char** argv)
{
    Mutex mutex;
    MutexTest test(mutex);
    test.start();

    // give thread a chance to acquire lock first
    sleep(1);

    // now it's main threads turn 
    printf("main waiting to get mutex\n");
    mutex.lock();
    printf("main got mutex lock\n");
    mutex.unlock();
    test.join();
    
    exit(0);
}

