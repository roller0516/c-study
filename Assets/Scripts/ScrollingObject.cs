using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ScrollingObject : MonoBehaviour
{
    public float speed = 0;

    private void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        if (GameManager.instance.isDead)
            return;
        if (gameObject.tag == "Cube" || gameObject.tag == "Item")
        {
            speed = GameManager.instance.MoveSpeed;
        }

        if (transform.position.x < -10 &&gameObject.tag == "Item")
            ObjectPool.instance.ReturnToPool("Item", gameObject);

        transform.Translate(Vector3.left * speed * Time.deltaTime,Space.World);
    }
}
