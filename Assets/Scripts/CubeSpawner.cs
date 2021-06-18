using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CubeSpawner : MonoBehaviour
{
    public GameObject cubePrefab;

    Renderer renderer;
    [SerializeField] int level = 0;

    LevelCtrl levelCtrl;
    List<LevelData> levelDatas;

    Vector3 lastCubePos;

    // Start is called before the first frame update
    void Start()
    {
        levelCtrl = GameManager.instance.LevelCtrl;
        levelCtrl.LoadData();
        levelDatas = levelCtrl.levelDatas;
        lastCubePos = new Vector3(0f, 0f, 0f);
    }

    // Update is called once per frame
    void Update()
    {
        if (level == 4) 
        {
            level = 4;
        }
        else if (Time.time >= levelDatas[level + 1].time)
        {
            level++;
        }
        //GameManager.instance.MoveSpeed = levelCtrl.levelDatas[level].speed; 
        if (GameManager.instance.MovedValue > lastCubePos.x - 20)
        {
            // 큐브 9개를 생성
            int randCount = Random.Range(levelDatas[level].floorMin, levelDatas[level].floorMax);
            int holeCount = Random.Range(levelDatas[level].holeMin, levelDatas[level].holeMax);
            int randY     = Random.Range(levelDatas[level].heightMin, levelDatas[level].heightMax);
            for (int i = 0; i < randCount; i++)
            {
               GameObject platForm = ObjectPool.instance.SpawnFromPool("PlatForm", lastCubePos
                + new Vector3(i - GameManager.instance.MovedValue, randY), Quaternion.Euler(0,90,0));

                renderer = platForm.GetComponent<Renderer>();
                switch (level)
                {
                    case 0:
                        renderer.material.color = new Color(255, 0, 0, 150);
                        break;
                    case 1:
                        renderer.material.color = new Color(0, 255, 0, 150);
                        break;
                    case 2:
                        renderer.material.color = new Color(0, 0, 255, 150);
                        break;
                    case 3:
                        renderer.material.color = new Color(255, 255, 255, 150);
                        break;
                }

            }
            lastCubePos = lastCubePos + new Vector3(holeCount+ randCount, 0f);
        }
    }
}
