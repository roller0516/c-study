using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FishObstacle : MonoBehaviour
{
    // Start is called before the first frame update
    Rigidbody rigid;

    public float jumpPower;
    bool isAlive;
    void Start()
    {
        isAlive = true;
        rigid = GetComponent<Rigidbody>();
    }

    // Update is called once per frame
    void Update()
    {
       transform.Translate(Vector3.left * 5 * Time.deltaTime,Space.World);
        if (isAlive) 
        {
            rigid.AddForce(new Vector3(0, jumpPower, 0));
            //isAlive = false;
        }
        if (transform.position.y > 2)
            isAlive = false;
    }
}
