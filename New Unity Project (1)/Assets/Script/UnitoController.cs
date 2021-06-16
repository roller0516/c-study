using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class UnitoController : MonoBehaviour
{
    public Vector3 startPos;
    public float jumpPower;
    new Rigidbody rigidbody;
    new Camera camera;
    Animator ani;
    Vector3 screenPos;
    RaycastHit rayhit;
    bool select = false;
    public List<GameObject> tileList;
    // Start is called before the first frame update
    void Start()
    {
        startPos = new Vector3(0, 1.5f, 0);
        rigidbody = GetComponent<Rigidbody>();
        ani = GetComponent<Animator>();
        camera = Camera.main;
    }

    void Update()
    {
        screenPos = camera.ScreenToWorldPoint(Input.mousePosition);
        for (int i = 0; i < tileList.Count; i++) 
        {
            Ray ray;
            ray = camera.ScreenPointToRay(Input.mousePosition);

            tileList[i].transform.position = new Vector3(screenPos.x + 7, 0, 0);
            if (Input.GetMouseButtonDown(0))
            {
                int randomNum = Random.Range(10, 15);
                SetScale(tileList[0], randomNum);
                Instantiate(tileList[0]);
            }
        }

        

        //if (Input.GetMouseButtonUp(0)) 
        //{
        //    rigidbody.AddForce(100, 100 + jumpPower, 0);
        //    jumpPower = 0;
        //}
        //isGround();
        //Move();
    }

    //void isGround() 
    //{
    //    if (transform.position.y < -5f) 
    //    {
    //        transform.position = startPos;
    //        rigidbody.Sleep();
    //    }
    //}
    void SetScale(GameObject obj,int size) 
    {
        obj.transform.localScale = new Vector3(10, size, 10);
    }
    void Move() 
    {
        ani.SetBool("IsMove", true);
        transform.Translate(Vector3.forward * 10 * Time.deltaTime);
    }
}
