using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CubeSpawner : MonoBehaviour
{
    public GameObject cubePrefab;

    Renderer renderer;
    [SerializeField] int level = 0;
    float timer;
    LevelCtrl levelCtrl;
    List<LevelData> levelDatas;
    [SerializeField] int Spawnpercentage;
    float spawnTime;
    Vector3 lastCubePos;

    // Start is called before the first frame update
    void Start()
    {
        levelCtrl = GameManager.instance.LevelCtrl;
        levelCtrl.LoadData();
        levelDatas = levelCtrl.levelDatas;
        lastCubePos = new Vector3(0f, 0f, 0f);
        Spawnpercentage = Random.Range(0, 10);
    }

    // Update is called once per frame
    void Update()
    {
        timer += Time.deltaTime;
        if (GameManager.instance.isDead)
            return;
        if (level == 4) 
        {
            level = 4;
        }
        else if (timer >= levelDatas[level + 1].time)
        {
            level++;
        }
        spawnTime += Time.deltaTime;
        if (spawnTime> Spawnpercentage) 
        {
            spawnTime = 0;
            Spawnpercentage = Random.Range(0, 10);
            ObjectPool.instance.SpawnFromPool("Obstacle", new Vector3(15, -2, 0), Quaternion.Euler(0, -90, 0));
        }

        GameManager.instance.MoveSpeed = levelCtrl.levelDatas[level].speed; 
        if (GameManager.instance.MovedValue > lastCubePos.x - 20)
        {
            // 큐브 9개를 생성
            int randCount = Random.Range(levelDatas[level].floorMin, levelDatas[level].floorMax);
            int holeCount = Random.Range(levelDatas[level].holeMin, levelDatas[level].holeMax);
            int randY     = Random.Range(levelDatas[level].heightMin, levelDatas[level].heightMax);
            for (int i = 0; i < randCount; i++)
            {
               ObjectPool.instance.SpawnFromPool("Floor", lastCubePos
                + new Vector3(i - GameManager.instance.MovedValue, randY), Quaternion.Euler(0,90,0));
               ObjectPool.instance.SpawnFromPool("Item", lastCubePos
               + new Vector3(i - GameManager.instance.MovedValue, randY+1), Quaternion.Euler(90, 0, 0));
            }
            lastCubePos = lastCubePos + new Vector3(holeCount+ randCount, 0f);
        }
    }
}
