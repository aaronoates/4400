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

#include <iostream>
#include "templates.h"
using namespace std;


int main()
{
	GrowableArray<int> i; // instance of growable array class of type integer
	i << 5;
	cout << i[0] << endl;
	GrowableArray<double> d; // same thing, type double
	d << 5.0;
	cout << d[0] << endl;
	GrowableArray<string> s; // same thing, type string
	s << "5";
	cout << s[0] << endl;
	GrowableArray<double> v;
	cout << v.average({2.0,2.0,2.0});

	//std::vector<GrowableArray<double>> piss = {1, 2, 3};
	//GrowableArray<double> values;
	

	//v << piss;
	

	
	return 0;
}