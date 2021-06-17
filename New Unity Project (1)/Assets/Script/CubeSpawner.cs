using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CubeSpawner : MonoBehaviour
{
    public GameObject cube;
    private float cooltime;
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        cooltime += 10*Time.deltaTime;
        if (cooltime > GameManager.instance.levelCtrl.levelDatas[GameManager.instance.level+1].time) 
        {
            cooltime = 0;
            Spawn();
        }
    }
    void Spawn() 
    {
        
        int min = GameManager.instance.levelCtrl.levelDatas[GameManager.instance.level].floorMin;
        int max = GameManager.instance.levelCtrl.levelDatas[GameManager.instance.level].floorMax;
        int randomNum = Random.Range(min, max);

        Instantiate(cube, new Vector3(0,randomNum,0), Quaternion.identity);
    }
}
