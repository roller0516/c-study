using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlatformSpawner : MonoBehaviour
{
    public GameObject platformPrefab;
    public int count = 6;

    GameObject[] platforms;
    int currentSpawnIndex = 0;

    Vector3 spwanerPos = new Vector3(0f, -25f, 0f);

    float lastSpawnTime = 0f;
    float timeBetSpawn = 0f;

    // Start is called before the first frame update
    void Start()
    {
        platforms = new GameObject[count];
        for (int i = 0; i < count; i++)
        {
            platforms[i] = Instantiate(platformPrefab, spwanerPos, Quaternion.identity);
        }
    }

    // Update is called once per frame
    void Update() // 오브젝트 풀링 
    {
        if (Time.time > lastSpawnTime + timeBetSpawn)
        {
            lastSpawnTime = Time.time;
            timeBetSpawn = Random.Range(2.5f, 3.5f);

            platforms[currentSpawnIndex].transform.position = new Vector3(12f, 0f, 0f);
            platforms[currentSpawnIndex].SetActive(false);
            platforms[currentSpawnIndex].SetActive(true);

            currentSpawnIndex++;

            if (currentSpawnIndex >= count)
            {
                currentSpawnIndex = 0;
            }
        }
    }
}
