using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.EventSystems;

public class UnitoController : MonoBehaviour
{
    public Vector3 startPos;

    new Rigidbody rigidbody;
    new SphereCollider collider;
    Animator animator;

    public float jumpPower = 700f;
    float maxJumpPower = 700f;

    int jumpCount = 0;
    bool isGrounded = false;
    bool isFalling = false;
    bool isDead = false;
    bool pressed = false;

    private void Awake()
    {
        
    }

    // Start is called before the first frame update
    void Start()
    {
        startPos = new Vector3(0f, 1.5f, 0f);
        rigidbody = GetComponent<Rigidbody>();
        collider = GetComponent<SphereCollider>();
        animator = GetComponent<Animator>();
    }
    
    public void OnPointerDown()
    {
        pressed = true;
    }
    public void OnPointerUp()
    {
        pressed = false;
    }
    // Update is called once per frame
    void Update()
    {
        if (isDead)
        {
            return;
        }

        
        #region JumpTest01
        //if (Input.GetMouseButton(0))
        //{
        //    jumpPower += 1f;
        //    if (jumpPower > maxJumpPower)
        //    {
        //        jumpPower = maxJumpPower;
        //    }
        //}
        //else if (Input.GetMouseButtonUp(0))
        //{
        //    rigidbody.AddForce(0f, jumpPower, 0f);
        //    jumpPower = 0f;
        //}        
        
        //if (transform.position.y < -5f)
        //{
        //    transform.position = startPos;
        //    transform.rotation = Quaternion.Euler(0f, 90f, 0f);
        //    jumpPower = 0f;
        //    rigidbody.Sleep();
        //}

        //float ratioY = Mathf.Clamp(1.0f - (jumpPower / maxJumpPower), 0.4f, 1f);
        //transform.localScale = new Vector3(
        //    transform.localScale.x,
        //    ratioY,
        //    transform.localScale.z);

        //collider.radius = ratioY;
        #endregion

        if (rigidbody.velocity.y < 0f)
        {
            isFalling = true;
        }
        else
        {
            isFalling = false;
        }

        animator.SetBool("Grounded", isGrounded);
        animator.SetBool("Falling", isFalling);

        //bug.Log(pressed);
        if (Input.GetMouseButtonDown(0) && jumpCount < 2)
        {
            jumpCount++;
            rigidbody.velocity = Vector3.zero;
            rigidbody.AddForce(0f, jumpPower, 0f);
        }
        else if (Input.GetMouseButtonDown(0) && rigidbody.velocity.y > 0)
        {
            rigidbody.velocity = rigidbody.velocity * 0.5f;
        }

    }

    void Die()
    {
        animator.SetTrigger("Die");

        rigidbody.Sleep();
        isDead = true;
    }
    private void OnTriggerEnter(Collider other)
    {
        if (other.tag == "Dead" && !isDead)
        {
            Die();
            GameManager.instance.isDead = true;
        }
        if (other.tag == "Item" )
        {
            GameManager.instance.Score += 1;
            ObjectPool.instance.ReturnToPool("Item", other.gameObject);
        }
    }

    private void OnCollisionEnter(Collision collision)
    {
        if(collision.contacts[0].normal.y > 0.7f)
        {
            isGrounded = true;
            jumpCount = 0;
        }
    }

    private void OnCollisionExit(Collision collision)
    {
        if (jumpCount > 0)
        {
            isGrounded = false;
        }
    }
}
