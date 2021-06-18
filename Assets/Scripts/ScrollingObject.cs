using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ScrollingObject : MonoBehaviour
{
    public float speed = 10f;

    private void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        if (gameObject.tag == "Cube")
        {
            speed = GameManager.instance.MoveSpeed;
        }
        transform.Translate(Vector3.left * speed * Time.deltaTime,Space.World);
    }
}
