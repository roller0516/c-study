using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class UnitoController : MonoBehaviour
{
    public AudioClip deathClip; // ����� ����� ����� Ŭ��
    public float jumpForce = 700f; // ���� ��

    public int jumpCount = 0; // ���� ���� Ƚ��
    private bool isGrounded = false; // �ٴڿ� ��Ҵ��� ��Ÿ��
    private bool isDead = false; // ��� ����

    private Rigidbody playerRigidbody; // ����� ������ٵ� ������Ʈ
    private Animator animator; // ����� �ִϸ����� ������Ʈ
    //private AudioSource playerAudio; // ����� ����� �ҽ� ������Ʈ

    private void Start()
    {
        // ���� ������Ʈ�κ��� ����� ������Ʈ���� ������ ������ �Ҵ�
        playerRigidbody = GetComponent<Rigidbody>();
        animator = GetComponent<Animator>();
    }

    private void Update()
    {
        if (isDead)
        {
            // ����� ó���� �� �̻� �������� �ʰ� ����
            return;
        }

        // ���콺 ���� ��ư�� �������� && �ִ� ���� Ƚ��(2)�� �������� �ʾҴٸ�
        if (Input.GetMouseButtonDown(0) && jumpCount < 2)
        {
            animator.SetBool("IsJumpUp", true);
            // ���� Ƚ�� ����
            jumpCount++;
            // ���� ������ �ӵ��� ���������� ����(0, 0)�� ����
            playerRigidbody.velocity = Vector2.zero;
            // ������ٵ� �������� ���� �ֱ�
            playerRigidbody.AddForce(new Vector2(0, jumpForce));
            // ����� �ҽ� ���
        }
        else if (Input.GetMouseButtonUp(0) && playerRigidbody.velocity.y > 0)
        {
            animator.SetBool("IsJumpUp", true);
            animator.SetBool("IsJumpDown", false);
            // ���콺 ���� ��ư���� ���� ���� ���� && �ӵ��� y ���� ������ (���� ��� ��)
            // ���� �ӵ��� �������� ����
            playerRigidbody.velocity = playerRigidbody.velocity * 0.5f;
        }
        else if (playerRigidbody.velocity.y < 0) 
        {
            animator.SetBool("IsJumpDown", true);
            animator.SetBool("IsJumpUp", false);
        }
            

        // �ִϸ������� Grounded �Ķ���͸� isGrounded ������ ����
        animator.SetBool("Grounded", isGrounded);
    }

    private void Die()
    {
        // �ִϸ������� Die Ʈ���� �Ķ���͸� ��
        animator.SetTrigger("Die");

        // ����� �ҽ��� �Ҵ�� ����� Ŭ���� deathClip���� ����
        //playerAudio.clip = deathClip;
        // ��� ȿ���� ���

        // �ӵ��� ����(0, 0)�� ����
        playerRigidbody.velocity = Vector2.zero;
        // ��� ���¸� true�� ����
        isDead = true;

        // ���� �Ŵ����� ���� ���� ó�� ����
        GameManager.instance.OnPlayerDead();
    }


    private void OnTriggerEnter(Collider other)
    {
        if (other.tag == "Dead" && !isDead)
        {
            // �浹�� ������ �±װ� Dead�̸� ���� ������� �ʾҴٸ� Die() ����
            Die();
        }
    }

    private void OnCollisionEnter(Collision collision)
    {
        // � �ݶ��̴��� �������, �浹 ǥ���� ������ ���� ������
        if (collision.contacts[0].normal.y > 0.7f)
        {
            // isGrounded�� true�� �����ϰ�, ���� ���� Ƚ���� 0���� ����
            isGrounded = true;
            jumpCount = 0;
        }
    }

    private void OnCollisionExit(Collision collision)
    {
        // � �ݶ��̴����� ������ ��� isGrounded�� false�� ����
        isGrounded = false;
    }
}
