/*
 * Copyright 2018 Jonathan Anderson
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

template<typename Iter, typename Comparator>
void bubbleSort(const Iter& begin, const Iter& end, Comparator compareFn){

}


template<typename Iter, typename Comparator>
void insertionSort(const Iter& begin, const Iter& end, Comparator compareFn){
    bool swapped;
    while (swapped) {
        swapped = false;
        Iter temporary_val;
        for (Iter *begin; Iter *begin <= end - 1; *begin++) {
            if (compareFn) {
                
            } else {
                temporary_val = *begin;
                *begin = *begin + 1;
                *begin + 1 = temporary_val;
                swapped = true;
            }
        }
    }
}

