using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[System.Serializable]
public struct LevelData
{
    public float time;
    public float speed;
    public int floorMin;
    public int floorMax;
    public int holeMin;
    public int holeMax;
    public int heightMin;
    public int heightMax;
}

public class LevelCtrl : MonoBehaviour
{
    //public TextAsset levelData;
    [SerializeField] 
    TextAsset levelData;
    //[SerializeField]
    public List<LevelData> levelDatas = new List<LevelData>();

    // Start is called before the first frame update
    void Start()
    {
        //LoadData();
    }

    // Update is called once per frame
    void Update()
    {

    }

    public void LoadData()
    {
        string text = levelData.text;

        string[] lines = text.Split('\n'); // \n -> ÁÙ¹Ù²Þ ¹®ÀÚ

        foreach (var line in lines)
        {
            if (line == "") break;

            string[] words = line.Split('\t');

            LevelData data = new LevelData();

            int index = 0;

            foreach (var word in words)
            {
                if (word == "") continue;
                if (word[0] == '#') break;

                switch (index)
                {
                    case 0: data.time = float.Parse(word); break;
                    case 1: data.speed = float.Parse(word); break;
                    case 2: data.floorMin = int.Parse(word); break;
                    case 3: data.floorMax = int.Parse(word); break;
                    case 4: data.holeMin = int.Parse(word); break;
                    case 5: data.holeMax = int.Parse(word); break;
                    case 6: data.heightMin = int.Parse(word); break;
                    case 7: data.heightMax = int.Parse(word); break;
                }
                index++;

                if (index >= 8)
                {
                    levelDatas.Add(data);
                }
            }
        }
    }
}