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
    for (Iter i = 0; i != end; i++) { //this is to ensure that if the final element needs to be sorted, it will not go out of range.
        for (Iter j = 0; j != end - 1; j++) {
            Iter place_holder; // if a swap needs to be made, it is temporarily assigned to this value.
            if (begin[j] > begin [j + 1]){
                place_holder = begin[j];
                begin[j] = begin[j + 1];
                begin[j + 1] = place_holder;
            }
        }
    }
}


template<typename Iter, typename Comparator>
void insertionSort(const Iter& begin, const Iter& end, Comparator compareFn){
    for(Iter i = begin; i != end; i++) { //this is to ensure that if the final element needs to be sorted, it will not go out of range.
        Iter key = *begin[i]; 
        Iter j = i - 1;


        while (j != end && compareFn(key,begin[j])) {
        
            begin[j + 1] = begin[j];
            j--;
        }
        
        *begin[j + 1] = key;
    }
    
}

