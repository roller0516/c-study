using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class GameManager : MonoBehaviour
{
    public static GameManager instance;

    LevelCtrl levelCtrl;
    public LevelCtrl LevelCtrl { get => levelCtrl; }
    CubeSpawner cubeSpawner;
    private int score;
    public Text scoreText;
    public Text levelText;
    public Image gameOver;
    public Image clear;
    public GameObject canvas;
    Animator canvasAni;

    float uiCooltime;
    public float MoveSpeed { get; set; }
    public float MovedValue { get; set; }
    public int Score { get => score; set => score = value; }

    public bool isDead;

    int count;

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
        canvasAni = canvas.GetComponent<Animator>();
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

        if (isDead) 
        {
            uiCooltime += Time.deltaTime;
            gameOver.gameObject.SetActive(true);
            if (uiCooltime > 1 && count==0) 
            {
                gameOver.gameObject.SetActive(false);
                canvas.SetActive(true);
                if (score > 150)
                {
                    canvasAni.SetTrigger("three");
                }
                else if (score > 100)
                {
                    canvasAni.SetTrigger("two");
                }
                else if (score > 50)
                {
                    canvasAni.SetTrigger("one");
                }
                else if (score > 10)
                {
                    canvasAni.SetTrigger("zero");
                }
                count++;
            }
        }
    }
    public void ReStartScene() 
    {
        SceneManager.LoadScene("SampleScene");
    }
}
