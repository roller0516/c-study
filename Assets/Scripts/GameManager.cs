using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class GameManager : MonoBehaviour
{
    public static GameManager instance;

    LevelCtrl levelCtrl;
    public LevelCtrl LevelCtrl { get => levelCtrl; }
    CubeSpawner cubeSpawner;
    private int score;
    public Text scoreText;
    public Text levelText;
    public float MoveSpeed { get; set; }
    public float MovedValue { get; set; }
    public int Score { get => score; set => score = value; }

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

        levelCtrl = GetComponent<LevelCtrl>();
        cubeSpawner = GetComponent<CubeSpawner>();
    }

    // Start is called before the first frame update
    void Start()
    {
        MoveSpeed = 4f;
        MovedValue = 0f;
    }

    // Update is called once per frame
    void Update()
    {
        scoreText.text = "Score : " + score;
        MovedValue += MoveSpeed * Time.deltaTime;
    }
}
