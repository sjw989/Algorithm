package com.example.algorithm;

import java.util.HashMap;

public class Lv2_캐시 {
    class City {
        public String name;
        public int used;
        public int time;

        public City(String name, int used, int time) {
            this.name = name;
            this.used = used;
            this.time = time;
        }
    }

    public int solution(int cacheSize, String[] cities) {
        int answer = 0;
        if (cacheSize == 0) {
            return cities.length * 5;
        }
        HashMap<String, City> cache = new HashMap();
        for (int i = 1; i <= cities.length; i++) {
            String cityName = cities[i - 1].toUpperCase();

            if (cache.get(cityName) != null) { // hit
                City city = cache.get(cityName);
                answer++;
                cache.replace(cityName, new City(city.name, city.used++, i));
            } else { // miss
                answer += 5;
                if (cache.size() == cacheSize) { // cache full
                    City removedCity = null;
                    for (String key : cache.keySet()) {
                        City comp = cache.get(key);
                        if (removedCity == null) {
                            removedCity = comp;
                        } else {
                            if (removedCity.used > comp.used) {
                                removedCity = comp;
                            } else if (removedCity.used == comp.used
                                    && removedCity.time > comp.time) {
                                removedCity = comp;
                            }
                        }
                    }
                    cache.remove(removedCity.name);
                }
                cache.put(cityName, new City(cityName, 1, i));
            }

        }
        return answer;
    }

}
