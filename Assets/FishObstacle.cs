using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FishObstacle : MonoBehaviour
{
    // Start is called before the first frame update
    Rigidbody rigid;

    public float speed;
    bool isAlive;
    void Start()
    {
        isAlive = true;
        rigid = GetComponent<Rigidbody>();
    }

    // Update is called once per frame
    void Update()
    {
       transform.Translate(Vector3.left * 10 * Time.deltaTime,Space.World);
        if (isAlive) 
        {
            transform.Translate(Vector3.up*Time.deltaTime * speed);
            rigid.useGravity = false;
        }
        if (transform.position.y > 2) 
        {
            isAlive = false;
            rigid.useGravity = true;
        }
    }
}
