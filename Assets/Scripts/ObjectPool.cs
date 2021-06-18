using System.Collections;
using System.Collections.Generic;
//using System;
using UnityEngine;

public class ObjectPool : MonoBehaviour
{
    public static ObjectPool instance;

    [System.Serializable]
    public class Pool 
    {
        public string tag;
        public GameObject prefab;
        public int size;
    }

    [SerializeField]
    List<Pool> pools;
    [SerializeField]
    Dictionary<string, Queue<GameObject>> poolDictionary;
    private void Awake()
    {
        if (instance == null)
        {
            instance = this;
        }
        else
        {
            Destroy(gameObject);
        }
    }
    // Start is called before the first frame update
    void Start()
    {
        poolDictionary = new Dictionary<string, Queue<GameObject>>();

        foreach (Pool pool in pools) 
        {
            Queue<GameObject> objcetPool = new Queue<GameObject>();
            for (int i = 0; i < pool.size; i++) 
            {
                GameObject obj =  Instantiate(pool.prefab);
                obj.SetActive(false);
                objcetPool.Enqueue(obj);
            }
            poolDictionary.Add(pool.tag, objcetPool);
        }
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    public GameObject SpawnFromPool(string tag, Vector3 position, Quaternion rotation) 
    {
        if (!poolDictionary.ContainsKey(tag)) 
        {
            Debug.LogError(tag + "가 없습니다");
            return null;
        }

        GameObject obj = poolDictionary[tag].Dequeue();

        obj.SetActive(true);
        obj.transform.position = position;
        obj.transform.rotation = rotation;

        return obj; 
    }

    public void ReturnToPool(string tag, GameObject obj) 
    {
        if (!poolDictionary.ContainsKey(tag))
        {
            Debug.LogError(tag + "가 없습니다");
            return;
        }
        obj.SetActive(false);
        poolDictionary[tag].Enqueue(obj);
    }
}
